const { SerialPort } = require('serialport')
const logs = document.getElementById('logs');
const comButtons = document.getElementById('comButtons');
let port = null;

async function listSerialPorts() {
  let paths = []
  await SerialPort.list().then((ports) => {
    ports.forEach(port => {
      var buttonPort = document.createElement("button");
      buttonPort.innerText = port.path
      buttonPort.id = port.path
      comButtons.appendChild(buttonPort)
      paths.push(port.path)
    });
  }).catch(err => {
    logs.innerText = 'Erreur lors de la recherche des ports série :' + err;
  });
  return paths
}

// Set a timeout that will check for new serialPorts every 2 seconds.
// This timeout reschedules itself.
//setTimeout(listPorts, 2000);

async function start() {
  listSerialPorts().then(paths => {
    paths.forEach(path => {
      document.getElementById(path).addEventListener("click", function() {connectToSerialPort(path)});
    })
  })
}

function connectToSerialPort(path) {
  port = new SerialPort({path: path, baudRate: 9600 });
  port.on('open', () => {
    logs.innerText = 'Connexion réussie à l\'Arduino.';
    console.log("test");
    // Envoyer des données à l'Arduino
  });
  port.on('error', err => {
    logs.innerText = 'Erreur de connexion à l\'Arduino :' + err;
  });
}

start();



const object = document.querySelector('.rotating-element');
const rotateBtn1 = document.getElementById('btn1');
const rotateBtn2 = document.getElementById('btn2');
const rotateBtn3 = document.getElementById('btn3');
const rotateBtn4 = document.getElementById('btn4');
const rotateBtn5 = document.getElementById('btn5');
const rotateBtn6 = document.getElementById('btn6');
const rotateBtn7 = document.getElementById('btn7');
const rotateBtn8 = document.getElementById('btn8');
const rotateBtn9 = document.getElementById('btn9');
const rotateBtn10 = document.getElementById('btn10');
const rotateBtn0 = document.getElementById('btn0');
const positionSpan = document.getElementById('positionNumber');
positionSpan.innerText = 0;


let rotationAngle = 0;
let lastPosition = 0;

rotateBridge(rotateBtn0,0);
rotateBridge(rotateBtn1,20);
rotateBridge(rotateBtn2,10);
rotateBridge(rotateBtn3,0);
rotateBridge(rotateBtn4,-10);
rotateBridge(rotateBtn5,-20);
rotateBridge(rotateBtn6,-30);
rotateBridge(rotateBtn7,-40);
rotateBridge(rotateBtn8,-50);
rotateBridge(rotateBtn9,-60);
rotateBridge(rotateBtn10,-70);


const buttonsList = document.getElementById("buttons");



function rotateBridge(rotateBtn, degre) {
  let position = null;
    rotateBtn.addEventListener('click', () => {
      console.log("appuie sur le bouton:" + rotateBtn);
      console.log(port);
        if(port != null){
          logs.innerText = 'Connexion réussie à l\'Arduino.';
          for (let i = 0; i < buttonsList.children.length; i++) {
            if(buttonsList.children[i] == rotateBtn){
                position = i;
            }
          }
          console.log(position);
          // Envoyer des données à l'Arduino
          port.write(position+"\n", (err) => {
            if (err) {
              logs.innerText = 'Erreur lors de l\'envoi des données :' + err;
            } else {
              rotationAngle = rotationAngle - lastPosition + degre; // Augmentez ou diminuez le nombre de degrés selon vos besoins
              object.style.transform = `rotate(${rotationAngle}deg)`;
              rotateBtn.disabled = true;
              lastPosition = degre;
              for (let i = 0; i < buttonsList.children.length; i++) {
                  if(buttonsList.children[i] !== rotateBtn){
                      buttonsList.children[i].disabled = false;
                  }
                  if(buttonsList.children[i] == rotateBtn){
                      positionSpan.innerText = `${i}`;
                  }
                }
              logs.innerText = 'Données envoyées avec succès.';
            }
          });
          port.on('error', err => {
            logs.innerText = 'Erreur de connexion à l\'Arduino :' + err;
          });
        }
    });
}
