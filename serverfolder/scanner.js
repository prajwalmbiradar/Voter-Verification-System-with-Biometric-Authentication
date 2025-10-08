let scanner;
const container = document.getElementById("scanner-container");
const resultDiv = document.getElementById("result");
const beep = document.getElementById("beep");

async function loadScanner() {
  // Ask for permission early
  try {
    await navigator.mediaDevices.getUserMedia({ video: true });
  } catch (e) {
    alert("Camera permission required to scan barcodes.");
    return;
  }

  // Configure SDK
  Dynamsoft.DBR.BarcodeScanner.engineResourcePath = "https://cdn.jsdelivr.net/npm/dynamsoft-javascript-barcode@9.6.21/dist/";
  Dynamsoft.DBR.BarcodeScanner.productKeys = ""; // Public trial
  await Dynamsoft.DBR.BarcodeScanner.loadWasm();

  if (scanner) {
    await scanner.destroyContext();
    container.innerHTML = "";
  }

  scanner = await Dynamsoft.DBR.BarcodeScanner.createInstance();
  await scanner.setUIElement(container); // Creates dce-video-container internally

  scanner.onUnduplicatedRead = (txt, result) => {
    beep.play();
    resultDiv.textContent = `✅ Scanned: ${txt}`;
    scanner.stopScanning();
  };

  await scanner.open();
  await scanner.startScanning();
}

function restartScan() {
  if (scanner) {
    scanner.startScanning();
    resultDiv.textContent = "📷 Scanning...";
  } else {
    loadScanner();
  }
}

window.onload = loadScanner;
