const { app, BrowserWindow } = require('electron/main')
const path = require('node:path')

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
        preload: path.join(__dirname, 'preload.js'),
        nodeIntegration: true,
        contextIsolation: false, // allow use with Electron 12+
    }
  })
  win.loadFile('index.html')
}

app.whenReady().then(() => {
  createWindow()
})