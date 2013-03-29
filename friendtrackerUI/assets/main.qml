// Navigation pane project template
import bb.cascades 1.0
import bb.system 1.0
import bb.cascades.maps 1.0

NavigationPane {
    id: navigationPane
    Menu.definition: MenuDefinition {
        // help action
        actions: [
            ActionItem {
            	title: "Info"
            	imageSource: "images/ic_info.png"
            	onTriggered: {
                	infoSheet.open();
                }
            }
        ]

        // settings action
        settingsAction: SettingsActionItem {
        	onTriggered: {
        	    _settings.initUserProfileFromBBM();
                navigationPane.push(settingsPage.createObject());
            }
    	}
    }
    
    onPopTransitionEnded: {
    	page.destroy();        
    }
    
    Page {
        actions: [
            ActionItem {
                title: _mapView.viewModeTitle
                imageSource: "asset:///images/bingmaps.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    _mapView.nextViewMode()
                    map.setMapType(_mapView.viewMode);
                }
            },
            ActionItem {
                title: "Center Me"
                imageSource: "asset:///images/pin.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    map.setCenter(_mapView.myLat, _mapView.myLon);
                }
            },
            ActionItem {
                title: "Friends"
                imageSource: "asset:///images/chat.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    console.log("showing friends javascript");
                    _mapView.showFriends()
                }
            }
        ]        
        Container {
            id: map
            layout: DockLayout {
            }
            
            //! [0]
            property variant center: [ "-1", "-1" ]
            property variant centerPixel: [ "-1", "-1" ]
            //! [0]
            
            //! [1]
            function setZoom(zoom) {
                var script = "setZoom(" + zoom + ")"
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function zoomIn() {
                var script = "zoomIn()"
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function zoomOut() {
                var script = "zoomOut()"
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function setCenter(lat, lon) {
                var script = "setCenter(" + lat + "," + lon + ")"
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function setMapType(mapType) {
                var script = "setMapTypeId(" + mapType + ")"
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function createPushPin(lat, lon, title) {
                var script = "createPushPin(" + lat + "," + lon + "," + "\"" + title + "\"" + "," + "\"local:///assets/images/pin.png\"" + ")"
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function removeAllPins() {
                var script = "removeAllPins()";
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function addOnlineFriend(friend) {
                var script = "addOnlineFriend(\"" + friend + "\")";
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function subscribe() {
                var script = "subscribe()";
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function unsubscribe() {
                var script = "unsubscribe()"
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function updateLocation(ppId, x, y, visibility) {
                var script = "updatePushPin(" + x + ", " + y + ", \"" + ppId + "\")";
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            function updateProfilePicture() {
                console.log("SIGNALLED UPDATEPROFILE PICTURE");
                var script = "updateProfilePicture()";
                qwvMapView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            //! [1]

            /*MapView {
                id: mapview
                altitude: 3000
                latitude: 43.449488
                longitude: -80.406777
                preferredWidth: 768
                preferredHeight: 1280
                onAltitudeChanged: {
                    //status.setText(qsTr("altitude changed: %1").arg(newAlt));
                }
                onHeadingChanged: {
                    //status.setText(qsTr("heading changed: %1").arg(newHeading));
                }
                onLatitudeChanged: {
                    //status.setText(qsTr("latitude changed: %1").arg(newLat));
                }
                onLongitudeChanged: {
                    //status.setText(qsTr("longitude changed: %1").arg(newLon));
                }
                onTiltChanged: {
                    //status.setText(qsTr("tilt changed: %1").arg(newTilt));
                }
                onMapLongPressed: {
                    //status.setText(qsTr("map long pressed"));
                }
                onRequestRender: {
                    //pinContainer.updateMarkers();
                }
            }*/

            ScrollView {
                id: scrollView
                scrollViewProperties {
                    scrollMode: ScrollMode.None
                    pinchToZoomEnabled: true
                }
                //! [2]
                WebView {
                    id: qwvMapView
            
                    html: _mapView.pageContent
                //! [2]
                
                	onCreationCompleted: {
                	    // connect to subscribe/unsubscribe signals from WebMaps
                        _mapView.subscribe.connect(map.subscribe);
                        _mapView.unsubscribe.connect(map.unsubscribe);
                        _mapView.friendLocationChanged.connect(map.updateLocation);
                        _friendtracker.updateProfilePictureOnMap.connect(map.updateProfilePicture);
                    }
                
                	onLoadingChanged: {
                	    if (loadRequest.status == WebLoadStatus.Succeeded) {
                	    	for (var i = 0; i < _friendtracker.onlinePpIds.length; i++) {
                	        	map.addOnlineFriend(_friendtracker.onlinePpIds[i]);
                	        }
                	    	map.subscribe();
                	    }                	                    	
                	}
            
                    onMinContentScaleChanged: {
                        scrollView.scrollViewProperties.minContentScale = minContentScale;
                    }
                    onMaxContentScaleChanged: {
                        scrollView.scrollViewProperties.maxContentScale = maxContentScale;
                    }
            
                    //! [3]
                    onMessageReceived: {
                        if (message.data.indexOf("centerChanged") >= 0) {
                            var data = message.data.substring(message.data.indexOf(":") + 1);
                            var values = data.split(",");
                            center = [
                                values[0],
                                values[1]
                            ];
                            centerPixel = [
                                values[2],
                                values[3]
                            ];
                            label.text = qsTr("centerChanged:\nWorld: %1, %2\nPixel: %3, %4")
                                             .arg(center[0].substr(0, 9)).arg(center[1].substr(0, 9))
                                             .arg(Math.round(x)).arg(Math.round(y));
                            labelPosition.positionX = centerPixel[0];
                            labelPosition.positionY = centerPixel[1];
                        } else if (message.data.indexOf("clicked") >= 0) {
                            var data = message.data.substring(message.data.indexOf(":") + 1);
                            var values = data.split(",");
                            var lat = values[0];
                            var lon = values[1];
                            var x = values[2];
                            var y = values[3];
                            label.text = qsTr("clicked:\nWorld: %1, %2\nPixel: %3, %4")
                                             .arg(lat.substr(0, 9)).arg(lon.substr(0, 9))
                                             .arg(Math.round(x)).arg(Math.round(y));
                            labelPosition.positionX = x;
                            labelPosition.positionY = y;
                        } else if (message.data.indexOf("markerClicked") >= 0) {
                            var data = message.data.substring(message.data.indexOf(":") + 1);
                            var values = data.split(",");
                            var lat = values[0];
                            var lon = values[1];
                            var x = values[2];
                            var y = values[3];
                            label.text = qsTr("markerClicked:\nWorld: %1, %2\nPixel: %3, %4")
                                             .arg(lat.substr(0, 9)).arg(lon.substr(0, 9))
                                             .arg(Math.round(x)).arg(Math.round(y));
                            labelPosition.positionX = x;
                            labelPosition.positionY = y;
                        }
                    }
                    //! [3]
            
                    //! [4]
                    gestureHandlers: [
                        PinchHandler {
                            property variant initial
                            onPinchUpdated: {
                                if (! initial) {
                                    initial = event.distance;
                                }
                                if ((event.distance - initial) / 50 > 1) {
                                    initial = event.distance;
                                    map.zoomIn();
                                } else if ((event.distance - initial) / 50 < -1) {
                                    initial = event.distance;
                                    map.zoomOut();
                                }
                            }
                        }
                    ]
                    //! [4]
                } // WebView
            } // ScrollView
        }       
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("NavigationPane - onCreationCompleted()");

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
    attachedObjects: [
        ComponentDefinition {
            id: settingsPage
            source: "settings.qml"
        },
        Sheet {
            id: infoSheet
            Info {
            	id: infoPage
                onDone: {
                    infoSheet.close();
                }
            }
        }
    ]
}
