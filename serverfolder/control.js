let vflag = 1;
const socket = io();
function ballot() {
    if (vflag) {
        document.getElementById('greenl').style.backgroundColor = 'rgb(0, 55, 0)'
        document.getElementById('redl').style.backgroundColor = 'rgb(255, 0, 0)'
        socket.emit('ballotg', 'ballot given');
        vflag = 0
    } else {
        console.log("not allowed");
    }
}
function response() {
    vflag = 1
    document.getElementById('greenl').style.backgroundColor = 'rgb(0, 255, 0)'
    document.getElementById('redl').style.backgroundColor = 'rgb(66, 0, 0)'
}
socket.on("cclear", (arg) => {
    console.log(arg); // world
    response();
});
socket.on("pressballot", (arg) => {
    console.log(arg); // world
    ballot();
});