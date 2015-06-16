/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

var home_marker = {lat: 42.3770, lng: -71.1256};

// info window
var info = new google.maps.InfoWindow();

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 42.3770, lng: -71.1256}, // Cambridge, Massachusetts
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
     var contentString = [];
    
     var parameters = {
        geo: place.postal_code
    };

    $.getJSON("articles.php", parameters)
    .done(function(data) {

         var items = []; 

        Object.keys(data).forEach(function(key) {
            items[key] = data[key];
        });

        Object.keys(items).forEach(function(i) {
            contentString += '<li><a href="' +
                items[i].link + '">' +
                items[i].title + '</a></li>';
        });

    });

    var image = 'img/announcements_256.png';
    var marker = new google.maps.Marker({
        position: new google.maps.LatLng(place.latitude, place.longitude),
        map: map,
        title: place.place_name,
        icon: image
    });

    markers.push(marker);

    google.maps.event.addListener(marker, 'click', function() {
        showInfo(marker, contentString);
    });
}

function setAllMap(map) {
    for (var i = 0; i < markers.length; i++) {
        markers[i].setMap(map);
    }
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p><%- place_name %>, <%- admin_code1 %>, <%- postal_code %></p>")
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

/**
 * Removes markers from map.
 */
function removeMarkers() {
    setAllMap(null);
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
            loadCrimes(data[i], 0.20);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
}

function loadCrimes(place, radius) {
    if (typeof(radius) === 'undefined' || radius === null) {
        radius = 0.020;
    }

    var url = "http://api.spotcrime.com/crimes.json?";
        url += "lat=" + place.latitude;
        url += "&lon=" + place.longitude;
        url += "&radius=" + radius;
        url += "&callback=?";
        url += "&key=spotcrime-private-api-key";

    $.getJSON(url, function(data) {
        if (data === null) {
            return;
        }

        var tableHTML = "<table>";
        var bounds = new google.maps.LatLngBounds();
        var totalCount = data.crimes.length;

        /* render points on map */
        $.each(data.crimes, function(index, crime) {
            var zIndex = totalCount - index;
            if (crime.type == "Other") {
                zIndex = 0;
            }

            var marker = new google.maps.Marker({
            map: map,
            position: new google.maps.LatLng(crime.lat, crime.lon),
            icon: imageForType(crime.type),
            title: crime.type,
            zIndex: zIndex
        });
      
        bounds.extend(marker.getPosition());
        var link = crime.link;
        link = link.replace('http://spotcrime.com/crime/', 'http://spotcrime.com/mobile/crime/?');

        var infowindow_content = "<div class='infowindow'><h4>"+crime.type+"</h4><p>"+crime.address+"</p><p>"+crime.date+"</p><p><a href='"+link+"' target='_blank'>More information at SpotCrime.com</a></p></div>";
        
        google.maps.event.addListener(marker, 'click', function(event) {
            showInfo(marker, infowindow_content);
        });

        markers.push(marker);

        tableHTML += "<tr id='" + crime.cdid + "' onclick='window.open(\"" + link + "\")'><td class='type'>";
        tableHTML += "<img src='" + imageForType(crime.type) + "' alt='" + crime.type + "'/>";
        tableHTML += "</td><td class='description'>";
        tableHTML += crime.type;
        tableHTML += " @ ";
        tableHTML += crime.address;
        tableHTML += "</td><td class='date'>";
        tableHTML += crime.date;
        tableHTML += "</td></tr>";
    });

    tableHTML += "</table>";
    $('#table_container').html(tableHTML);
});
}
function imageForType(type) {
  var root = "/public/";
  root += "img/"; 
  return root + {
    "Theft": 'theft',
    "Robbery": 'robbery',
    "Burglary": 'burglary',
    "Vandalism": 'vandalism',
    "Shooting": 'shooting',
    "Arson": 'arson',
    "Arrest": 'arrest',
    "Assault": 'assault',
    "Other": 'other'
  }[type] + '.png';
}


