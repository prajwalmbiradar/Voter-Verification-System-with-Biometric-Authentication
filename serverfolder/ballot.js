let vflag = 0;

const socket = io();
function su(q) {
    if (vflag) {
        
        

        vflag = 0
    p = (q-1)

    var fn = 's' + q;
    
    fn = fn + '.jpg'
    
    vv = document.getElementById('ss');
    vm = document.getElementById('cname');
    vm.innerHTML = q;
 console.log(vv);
 vv.src = fn
 console.log(vv);
    e = document.getElementsByClassName("buttonc");
    ce = e[p].querySelectorAll('div.arr-image img');
    ce[0].src = "ll.png"
    var ae = document.getElementById('cover');
    ae.style.height = '0px';

    setTimeout(() => {
       ce[0].src = "l.png"
       
    }, 300);
    setTimeout(() => {
        ae.style.height = '100px';
        setTimeout(() => {
            e = document.getElementById('glight');
            socket.emit('voted','user voted');
            e.style.backgroundColor = 'red'
        }, 1500);
       

       
     }, 5000);


    } else {
        console.log('not allowed');
    }
}
function allowvote() {
    vflag = 1;
    e = document.getElementById('glight');
    e.style.backgroundColor = 'green'
}
socket.on("bclear", (arg) => {
    console.log(arg); // world
    allowvote();
  
  });