# Voter Verification System with Biometric Authentication

A comprehensive electronic voting system implementation combining biometric verification, electronic ballot units, and real-time vote tracking. This project demonstrates a complete e-voting stack with hardware and software components.


## Features

- 🔐 Multi-factor voter authentication:
  - Barcode/QR code scanning for voter ID
  - Biometric fingerprint verification
  - Real-time identity validation
- 📱 Modern web interfaces:
  - Live vote tracking dashboard
  - Control unit interface
  - Electronic ballot unit display
  - Administrative portal
- 🔒 Security measures:
  - Firebase Realtime Database with rules
  - Secure WebSocket communication
  - Hardware-level vote verification
  - Encrypted data transmission
- 📊 Real-time analytics:
  - Gender-wise vote distribution
  - Live turnout percentages
  - Remaining voter counts
  - Comprehensive voting statistics

## System Architecture

The system consists of three main components:

### 1. Hardware Layer (ESP32/Arduino)
- **Components:**
  - ESP32 microcontroller
  - Fingerprint sensor module
  - 16x2 LCD display
  - 4x4 Matrix keypad
  - Indicator LEDs
  - Buzzer for audio feedback
  
- **Features:**
  - Voter ID input and verification
  - Fingerprint scanning and matching
  - Real-time status display
  - Hardware-level vote validation
  - Serial communication with server

### 2. Server Layer (Node.js)
- **Components:**
  - Express.js HTTPS server
  - Socket.IO for real-time updates
  - Firebase Admin SDK integration
  - Serial port communication
  
- **Features:**
  - Secure HTTPS endpoints
  - Real-time WebSocket events
  - Firebase data synchronization
  - Hardware-software bridge
  - Vote count management

### 3. Frontend Layer (Web)
- **Components:**
  - Real-time dashboard
  - Ballot unit interface
  - Control unit display
  - Administrative controls
  
- **Features:**
  - Live vote tracking
  - Interactive ballot display
  - Real-time statistics
  - Responsive design
  - Chart.js visualizations

## Prerequisites

- Hardware:
  - ESP32 or compatible Arduino board
  - Fingerprint sensor (tested with Adafruit)
  - 16x2 I2C LCD display
  - 4x4 Matrix keypad
  - LEDs and buzzer
  
- Software:
  - Node.js v16+
  - Arduino IDE
  - Firebase account
  - Required libraries:
    - Arduino: `Adafruit_Fingerprint`, `LiquidCrystal_I2C`, `Keypad`
    - Node.js: `firebase-admin`, `socket.io`, `serialport`

## Installation

1. **Hardware Setup:**
   ```bash
   # Upload ESP32 code
   cd esp\ code/
   # Open code.ino in Arduino IDE
   # Install required libraries through Library Manager
   # Select your board and port
   # Upload the sketch
   ```

2. **Server Setup:**
   ```bash
   # Install dependencies
   npm install

   # Configure environment
   cp .env.example .env
   # Edit .env with your Firebase credentials

   # Start server
   node ballotcpu.js
   ```

3. **Frontend Setup:**
   ```bash
   # Serve frontend files
   cd serverfolder/
   # Configure Firebase in dashboard.js
   # Open main.html in browser
   ```

## Security Considerations

1. **Firebase Security:**
   - Store service account key securely
   - Configure proper database rules
   - Use environment variables

2. **Hardware Security:**
   - Physical access controls
   - Tamper detection
   - Secure communication

3. **Software Security:**
   - HTTPS endpoints
   - WebSocket validation
   - Input sanitization

## Development Workflow

1. Set up development environment as described above
2. Configure hardware connections per schematic
3. Update Firebase credentials in configuration
4. Start server and verify connectivity
5. Test vote flow end-to-end

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

## Directory Structure

```
├── ballotcpu.js              # Main Node.js server
├── esp code/
│   └── code.ino              # ESP32/Arduino firmware
├── serverfolder/             # Frontend web files
│   ├── ballot.html/js/css    # Ballot unit interface
│   ├── control.html/js/css   # Control unit interface
│   ├── dashboard.html/js/css # Statistics dashboard
│   └── scanner.html/js/css   # QR code scanner interface
└── config/                   # Configuration files
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

- Adafruit for fingerprint sensor library
- Chart.js for visualization
- Socket.IO for real-time capabilities
- Firebase for backend services
