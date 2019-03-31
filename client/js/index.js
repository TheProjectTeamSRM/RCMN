//var socket = io();

var list_id = 0;
var m_index = 0;
var lat_gl = [12.823109, 12.823109, 12.823109];
var lon_gl = [80.041021, 80.041021, 80.041021];

var lat1 = 12.823109;
var lon1 = 80.041021;

/*
socket.on('alerts', function(msg) {

    console.log('message: ' + msg);
    var trim_msg = msg.substring(0, 50);

    list_id++;
    var a = list_id.toString();
    x = 'list_item_' + a;
    y = 'list_btn_' + a;
    console.log('a= ' + a);


    var node = document.createElement("LI");
    node.classList.add("collection-item");
    node.setAttribute("id", x);


    node.innerHTML = trim_msg + "<span class=\"new badge\" data-badge-caption=\"Raise Ticket\" id=" + y + " onclick=\"raise_ticket(id)\"/>"
    document.getElementById("abox").appendChild(node);

});


socket.on('r_tickets', function(msg) {

    console.log('message: ' + msg);
    var trim_msg = msg.substring(0, 50);

    var node = document.createElement("LI");
    node.classList.add("collection-item");
    node.setAttribute("id", x);


    node.innerHTML = trim_msg;
    document.getElementById("tbox").appendChild(node);

});

*/

function raise_ticket() {
    var node = document.createElement("LI");
    node.classList.add("collection-item");
    node.setAttribute("id", x);
    node.innerHTML = "A ticket has been raised for Alert : A1";
    document.getElementById("tbox").appendChild(node);
}

function showMap() {


    var mymap = L.map('mapid').setView([26.20, 91.67], 153);



    L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoidGVrbmljdXMiLCJhIjoiY2p0NTB5ZXZyMDFqNzQ5bzZ5ZDBodXViYyJ9.SuiIDJWFCq7kPqdXD9i67w', {
        maxZoom: 18,
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' +
            '<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
            'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
        id: 'mapbox.streets'
    }).addTo(mymap);

    markers = [
        {
            "name": "Pothole 1",
            "url": "https://en.wikipedia.org/wiki/Canada",
            "lat": 26.206915,
            "lng": 91.675675
        },
        {
            "name": "Pothole 2",
            "url": "https://en.wikipedia.org/wiki/Anguilla",
            "lat": 26.205043,
            "lng": 91.674202
        },
        {
            "name": "Pothole 3",
            "url": "https://en.wikipedia.org/wiki/Japan",
            "lat": 26.203734,
            "lng": 91.673726
        },
        {
            "name": "Pothole 4",
            "url": "https://en.wikipedia.org/wiki/Japan",
            "lat": 26.197791,
            "lng": 91.673098
        },
        {
            "name": "Pothole 5",
            "url": "https://en.wikipedia.org/wiki/Japan",
            "lat": 26.196291,
            "lng": 91.671044
        }
    ];


    var myIconr = L.icon({
        iconUrl: 'https://teknicus.github.io/images/images/pin24r.png',
        iconRetinaUrl: 'https://teknicus.github.io/images/images/pin48r.png',
        iconSize: [29, 24],
        iconAnchor: [9, 21],
        popupAnchor: [0, -14]
    });

    var myIcony = L.icon({
        iconUrl: 'https://teknicus.github.io/images/images/pin24y.png',
        iconRetinaUrl: 'https://teknicus.github.io/images/images/pin48y.png',
        iconSize: [29, 24],
        iconAnchor: [9, 21],
        popupAnchor: [0, -14]
    });

    var myIconb = L.icon({
        iconUrl: 'https://teknicus.github.io/images/images/pin24b.png',
        iconRetinaUrl: 'https://teknicus.github.io/images/images/pin48b.png',
        iconSize: [29, 24],
        iconAnchor: [9, 21],
        popupAnchor: [0, -14]
    });
/*
    for ( var i=0; i < markers.length; ++i )
    {
        L.marker( [markers[i].lat, markers[i].lng], {icon: myIcon} )
            .bindPopup( '<a href="' + markers[i].url + '" target="_blank">' + markers[i].name + '</a>' )
            .addTo( mymap );
    }
*/
    L.marker( [markers[0].lat, markers[0].lng], {icon: myIconr} )
        .bindPopup( '<a href="' + markers[0].url + '" target="_blank">' + markers[0].name + '</a>' )
        .addTo( mymap );
    L.marker( [markers[1].lat, markers[1].lng], {icon: myIcony} )
        .bindPopup( '<a href="' + markers[1].url + '" target="_blank">' + markers[2].name + '</a>' )
        .addTo( mymap );
    L.marker( [markers[2].lat, markers[2].lng], {icon: myIcony} )
        .bindPopup( '<a href="' + markers[2].url + '" target="_blank">' + markers[2].name + '</a>' )
        .addTo( mymap );
    L.marker( [markers[3].lat, markers[3].lng], {icon: myIconr} )
        .bindPopup( '<a href="' + markers[3].url + '" target="_blank">' + markers[3].name + '</a>' )
        .addTo( mymap );
    L.marker( [markers[4].lat, markers[4].lng], {icon: myIconb} )
        .bindPopup( '<a href="' + markers[4].url + '" target="_blank">' + markers[4].name + '</a>' )
        .addTo( mymap );
/*
        for ( var i=0; i < markers.length; ++i )
        {
            L.marker( [markers[i].lat, markers[i].lng] )
                .bindPopup( '<a href="' + markers[i].url + '" target="_blank">' + markers[i].name + '</a>' )
                .addTo( mymap );
        }
        */
    /*
    for ( var i=0; i < markers.length; ++i )
    {
        L.marker( [markers[i].lat, markers[i].lng], {icon: myIcon} )
            .bindPopup( '<a href="' + markers[i].url + '" target="_blank">' + markers[i].name + '</a>' )
            .addTo( mymap );
    }
*/


    /*
        var mymap = L.map('mapid').setView([12.823109, 80.041021], 13);


        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoidGVrbmljdXMiLCJhIjoiY2p0NTB5ZXZyMDFqNzQ5bzZ5ZDBodXViYyJ9.SuiIDJWFCq7kPqdXD9i67w', {
            maxZoom: 18,
            attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' +
                '<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
                'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
            id: 'mapbox.streets'
        }).addTo(mymap);

        var lati = 12.823109;
        var longi = 80.041021;

        var lati1 = 12.834209;
        var longi1 = 80.052121;

        var lati2 = 12.844309;
        var longi2 = 80.062221;
        var marker = L.marker([lati, longi]).addTo(mymap);
        var marker = L.marker([lati1, longi1]).addTo(mymap);
        var marker = L.marker([lati2, longi2]).addTo(mymap);
        */
}

function findAlerts() {
    fetch('http://localhost:3000/alerts')
        .then(
            function(response) {
                if (response.status !== 200) {
                    console.log('Looks like there was a problem. Status Code: ' +
                        response.status);
                    return;
                }

                // Examine the text in the response.
                response.json().then(function(data) {
                    //console.log(data);
                    console.log("Pothole Detected at " + data[0].latitude);




                    list_id++;

                    var i;
                    for (i = 0; i < data.length; i++) {
                        //for(i=0, i<data.length(), ++i) {
                        var datadump = JSON.stringify(data[i]);
                        console.log(datadump);var a = list_id.toString();
                        var trim_msg = datadump.substring(35, 97);

                        x = 'list_item_' + a;
                        y = 'list_btn_' + a;
                        console.log('a= ' + a);


                        var node = document.createElement("LI");
                        node.classList.add("collection-item");
                        node.setAttribute("id", x);


                        node.innerHTML = trim_msg + "<span class=\"new badge\" data-badge-caption=\"Raise Ticket\" id=" + y + " onclick=\"raise_ticket(id)\"/>"
                        document.getElementById("abox").appendChild(node);
                    }

                });
            }
        )
}
