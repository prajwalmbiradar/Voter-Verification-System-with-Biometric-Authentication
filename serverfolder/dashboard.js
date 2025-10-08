import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
import { getAnalytics } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-analytics.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-database.js";

// Firebase config
const firebaseConfig = {
  apiKey: "",
  authDomain: "votingdata.firebaseapp.com",
  projectId: "votingdata",
  storageBucket: "votingdata.appspot.com",
  messagingSenderId: "8127",
  appId: "1:83027:web:2c5600a4fba",
  measurementId: "G-7B"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
const database = getDatabase(app, 'https://votingdatdefault-rtdb.asia-southeast1.firebasedatabase.app');

// Reference to 'votes' node
const votesRef = ref(database, 'votes');
console.log("📡 Listening to Firebase...");
onValue(votesRef, (snapshot) => {
  console.log("🔥 onValue triggered");
  const data = snapshot.val();
  console.log("🧠 Data:", data);
});

// Total registered voters
const totalMen = 12;
const totalWomen = 8;
const totalVoters = totalMen + totalWomen;

// Listen for changes
onValue(votesRef, (snapshot) => {
  const data = snapshot.val();
  if (!data) {
    console.error("❌ No data found at 'votes' node.");
    return;
  }

  const votedMen = data.menvotes || 0;
  const votedWomen = data.womenvotes || 0;
  const totalVoted = votedMen + votedWomen;
  const remainingMen = totalMen - votedMen;
  const remainingWomen = totalWomen - votedWomen;
  const remainingVoters = remainingMen + remainingWomen;
  console.log(votedMen);
  console.log(votedWomen);
  
  

  // DOM update
  document.getElementById('totalVotes').innerText = totalVoted;

  // Chart: Total Votes (Doughnut)
  new Chart(document.getElementById('totalVotesChart').getContext('2d'), {
    type: 'doughnut',
    data: {
      labels: ['Voted', 'Remaining'],
      datasets: [{
        data: [totalVoted, totalVoters - totalVoted],
        backgroundColor: ['#4caf50', '#f44336']
      }]
    },
    options: { responsive: true, maintainAspectRatio: true }
  });

  // Chart: Men Votes (Bar)
  new Chart(document.getElementById('menVotesChart').getContext('2d'), {
    type: 'bar',
    data: {
      labels: ['Men Voted'],
      datasets: [{
        data: [votedMen],
        backgroundColor: ['#2196f3']
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        y: { beginAtZero: true, max: totalMen }
      }
    }
  });

  // Chart: Women Votes (Bar)
  new Chart(document.getElementById('womenVotesChart').getContext('2d'), {
    type: 'bar',
    data: {
      labels: ['Women Voted'],
      datasets: [{
        data: [votedWomen],
        backgroundColor: ['#ff4081']
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        y: { beginAtZero: true, max: totalWomen }
      }
    }
  });

  // Chart: Total Voting Percentage
  new Chart(document.getElementById('totalPercentageChart').getContext('2d'), {
    type: 'bar',
    data: {
      labels: ['Total Voting %'],
      datasets: [{
        data: [(totalVoted / totalVoters) * 100],
        backgroundColor: ['#4caf50']
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        y: { beginAtZero: true, max: 100 }
      }
    }
  });

  // Chart: Men Voting Percentage
  new Chart(document.getElementById('menPercentageChart').getContext('2d'), {
    type: 'bar',
    data: {
      labels: ['Men Voting %'],
      datasets: [{
        data: [(votedMen / totalMen) * 100],
        backgroundColor: ['#2196f3']
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        y: { beginAtZero: true, max: 100 }
      }
    }
  });

  // Chart: Women Voting Percentage
  new Chart(document.getElementById('womenPercentageChart').getContext('2d'), {
    type: 'bar',
    data: {
      labels: ['Women Voting %'],
      datasets: [{
        data: [(votedWomen / totalWomen) * 100],
        backgroundColor: ['#ff4081']
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        y: { beginAtZero: true, max: 100 }
      }
    }
  });

  // Chart: Remaining Votes (Doughnut)
  new Chart(document.getElementById('remainingVotesChart').getContext('2d'), {
    type: 'doughnut',
    data: {
      labels: ['Remaining Men', 'Remaining Women'],
      datasets: [{
        data: [remainingMen, remainingWomen],
        backgroundColor: ['#ff5722', '#ffeb3b']
      }]
    },
    options: { responsive: true, maintainAspectRatio: true }
  });

  // Chart: Remaining Voting Percentage
  new Chart(document.getElementById('remainingPercentageChart').getContext('2d'), {
    type: 'bar',
    data: {
      labels: ['Remaining Voting %'],
      datasets: [{
        data: [(remainingVoters / totalVoters) * 100],
        backgroundColor: ['#f44336']
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        y: { beginAtZero: true, max: 100 }
      }
    }
  });
});
