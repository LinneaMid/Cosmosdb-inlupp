let tabledata = document.getElementById('tabledata')

fetch("https://iot20-lin-fa.azurewebsites.net/api/GetAllFromCosmosDb")
.then(res => res.json())
.then(data => {
    console.log(data)
    for(let row of data) {

        var unixTimestamp = row.ts;
        var date = new Date(unixTimestamp*1000);

        tabledata.innerHTML += `<tr><td>${row.deviceIds}</td><td>${date}</td><td>${row.temp}</td><td>${row.hum}</td>`
    }
})