//
//  ViewController.swift
//  rebounder_ble
//
//  Created by Luz Camacho on 4/19/21.
//

import UIKit
import CoreBluetooth

class ViewController: UIViewController, CBCentralManagerDelegate, CBPeripheralDelegate {
    
    @IBOutlet weak var segmentControl: UISegmentedControl!
    @IBOutlet weak var descriptionLabel: UILabel!
    var centralManager: CBCentralManager!
    var blePeripheral: CBPeripheral!
    var modeChar: CBCharacteristic!
    var currMode: UInt8 = 0
    var isInit: Bool = false
    
    /*@IBAction func didChangeSegmentControl(_ sender: Any) {
        if (segmentControl.selectedSegmentIndex == 0) {
            descriptionLabel.text = "The auto track ..."
        } else if (segmentControl.selectedSegmentIndex == 1) {
            descriptionLabel.text = "The manual track ..."
        } else if (segmentControl.selectedSegmentIndex == 2) {
            descriptionLabel.text = "The sequence ..."
        }
    } */
    
    @IBAction func didChangeSegmentControl(_ sender: Any) {
        print("Writing new data")
        currMode = UInt8(segmentControl.selectedSegmentIndex)
        let writableData = Data([currMode])
        blePeripheral.writeValue(writableData, for: modeChar, type: CBCharacteristicWriteType.withResponse)
        descriptionLabel.text = getModeStr(from: currMode)
    }
    
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        var poweredOn = false;
        switch central.state {
            case CBManagerState.poweredOn:
                poweredOn = true
                print("BLE powered on.")
            case CBManagerState.poweredOff:
                print("BLE powered off")
            case CBManagerState.unauthorized:
                print("Unauthorized to use BLE")
            default:
                print("State undefined")
        }
        
        if(poweredOn) {
            central.scanForPeripherals(withServices: nil, options: nil)
        }
    }
    
    // called whenever the device scans and finds a peripheral 
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if let pname = peripheral.name {
            if(pname == "BLE_LUZ") {
                print("Found rebounder ble. Connecting...")
                self.centralManager.stopScan()
                self.blePeripheral = peripheral
                self.blePeripheral.delegate = self
                self.centralManager.connect(peripheral, options: nil)
            }
        }
    }
    
    // called on connection to the peripheral
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        print("Connected to rebounder ble!")
        self.blePeripheral.discoverServices(nil)
    }
    
    // called on disconnect
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        print("Disconnected from ble peripheral")
    }
    
    // called to discover services provided by the peripheral
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        if(error == nil) {
            if(peripheral.services != nil) {
                for service in peripheral.services! {
                    print(service) // really banking on the fact that there is only 1 service atm 
                    peripheral.discoverCharacteristics(nil, for: service)
                }
            } else {
                print("BLE rebounder provides no services")
            }
        } else {
            print(error!)
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        guard let characteristics = service.characteristics else { return }
        // truly expecting only one characteristic in this service, please
        for characteristic in characteristics {
            if(characteristic.properties.contains(.read) && characteristic.properties.contains(.write)) {
                print("Found mode switch characteristic/service!")
                modeChar = characteristic
                // at this point it is safe to try to read the value from the characteristic
                blePeripheral.readValue(for: modeChar)
            }
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        let charData = characteristic.value
        let byte = charData?.first
        if byte != nil {
            currMode = byte ?? 0
            if(isInit == false) {
                initView()
                isInit = true
            }
        } else {
            print("Unable to parse characteristic value")
        }
    }
    
    func printModeStr() {
        switch currMode {
            case 0: print("player_track")
            case 1: print("manual_control")
            case 2: print("sequence_upload")
            default: print("unknown mode value")
        }
    }
    
    func getModeStr(from segment: UInt8) -> String {
        switch segment {
        case 0:
            return "Auto Track Mode: Have the rebounder automatically track the player and move the shoot to follow the player's position."
        case 1:
            return "Manual Control: Take control of the rebounder directly by moving the controls on the control box."
        case 2:
            return "Sequence Uploaded: Have the rebounder move the shoot according to the uploaded sequence. WIP."
        default:
            return "Unkown Mode Value"
        }
    }
    
    
    
    func initView() {
        // adjust current mode
        if(currMode > 2 || currMode < 0) {
            print("Unknown Mode Value")
            return
        } else {
            print("New mode is \(currMode)")
        }
        segmentControl.selectedSegmentIndex = Int(currMode)
        descriptionLabel.text = getModeStr(from: currMode)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }


}

