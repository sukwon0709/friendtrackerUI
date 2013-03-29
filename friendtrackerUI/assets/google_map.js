/*
 * Copyright 2010-2011 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// initialize the map
var googleMap;
var markersArray = [];
var friends = [];
var websocket = null;

// pushpin for the user
var mypin;
var friendsPins = {};

// hack to get around image caching on user's profile picture
var counter = 1;

function initMaps(lat, lng) {
    console.log("init GoogleMaps @" + lat + "," + lng);
    var myLat = lat;
    var myLong = lng;
    var myLocation = new google.maps.LatLng(myLat, myLong);

    var mapOptions = {
        zoom : 14,
        center : myLocation,
        mapTypeId : google.maps.MapTypeId.HYBRID,
        mapTypeControl : false,
        zoomControl : false,
        streetViewControl : false,
        styles : [ {
            featureType : "poi",
            elementType : "labels",
            stylers : [ {
                visibility : "off"
            } ]
        } ]
    };
    googleMap = new google.maps.Map(document.getElementById("map_canvas"),
            mapOptions);

    google.maps.event.addListener(googleMap, 'click', clicked);
    google.maps.event.addListener(googleMap, 'center_changed', centerChanged);
    
    createPushPin(myLat, myLong, "Me", "local:///assets/profile.jpg");

    console.log("Done init GoogleMaps");
}

function updateProfilePicture() {
	var prevPin = friendsPins["Me"];
	var lat = prevPin.getLocation().latitude;
	var lon = prevPin.getLocation().longitude;
	console.log("UPDATE PROFILE PICTURE JAVASCRIPT " + lat + "," + lon);
	prevPin.setMap(null);
	
	var path = "local:///assets/profile" + counter.toString() + ".jpg";
	createPushPin(lat, lon, "Me", path);
	counter = counter + 1;
}

function addOnlineFriend(friend) {
	friends.push(friend);
}

function subscribe() {
	websocket = startSubscription(friends, this);
}

function unsubscribe() {
	endSubscription(friends, websocket);
}

function plot(data) {
	if (data.user in friendsPins) {
		updatePushPin(data.location.x, data.location.y, data.user, placeholderImage);
	} else {
		createPushPin(data.location.x, data.location.y, data.user, placeholderImage);	
	}
}

function clicked(event) {
    var point = convertPoint(event.latLng);
    navigator.cascades.postMessage("clicked:" + event.latLng.lat() + "," + event.latLng.lng() + "," + point.x + "," + point.y);
}

function centerChanged() {
    var point = convertPoint(googleMap.getCenter());
    navigator.cascades.postMessage("centerChanged:" + googleMap.getCenter().lat() + "," + googleMap.getCenter().lng() + "," + point.x + "," + point.y);

}

function onMessage(message) {

}

function setZoom(zoom) {
    googleMap.setZoom(zoom);
}

//! [2]
function zoomIn() {
    googleMap.setZoom(googleMap.getZoom()+1);
}

function zoomOut() {
    googleMap.setZoom(googleMap.getZoom()-1);
}
//! [2]

function setCenter(lat, lon) {
    var center = new google.maps.LatLng(lat, lon);
    googleMap.setCenter(center);
}

function setMapTypeId(mapType) {
    googleMap.setMapTypeId(mapType);
}

//create a marker / push-pin
function createPushPin(lat, lon, title, icon) {
    var placeLoc = new google.maps.LatLng(lat, lon);
    var marker = new google.maps.Marker({
    	title: title,
        map : googleMap,
        position : placeLoc,
        draggable : false,
        animation : google.maps.Animation.DROP,
        icon : icon,
        anchor: new google.maps.Point(52,112)
    });
    google.maps.event.addListener(marker, 'click', markerClicked);
    markersArray.push(marker);
}

function updatePushPin(lat, lon, title) {
	var pin = friendsPins[title];
	pin.setPosition(new google.maps.LatLng(lat, lon));
}

function removeAllPins() {
    if (markersArray) {
        for (i in markersArray) {
            markersArray[i].setMap(null);
        }
    }
}

function markerClicked(event) {
    var point = convertPoint(event.latLng);
    navigator.cascades.postMessage("markerClicked:" + event.latLng.lat() + "," + event.latLng.lng() + "," + point.x + "," + point.y);
}

function convertPoint(latLng) {
    var topRight=googleMap.getProjection().fromLatLngToPoint(googleMap.getBounds().getNorthEast());
    var bottomLeft=googleMap.getProjection().fromLatLngToPoint(googleMap.getBounds().getSouthWest());
    var scale=Math.pow(2,googleMap.getZoom());
    var worldPoint=googleMap.getProjection().fromLatLngToPoint(latLng);
    return new google.maps.Point((worldPoint.x- bottomLeft.x)*scale,(worldPoint.y-topRight.y)*scale);
}
