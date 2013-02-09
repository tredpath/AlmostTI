// Default empty project template
import bb.cascades 1.0

// creates one page with a label

NavigationPane {
    id: navigationPane
    objectName: "navigationPane"
    backButtonsVisible: true
    
	Menu.definition: MenuDefinition {
		actions: [
			ActionItem {
				title: "Open ROM"
				imageSource: "asset:///open.png"
				
				onTriggered: {
				    var romPage = romselector.createObject();
                    navigationPane.push(romPage)
				}
			},
			ActionItem {
				title: "ROM Info"
				imageSource: "asset:///file_info.png"
				
				onTriggered: {
				    var romInfoPage = rominfo.createObject()
				    navigationPane.push(romInfoPage)
				}
			},
			ActionItem {
				title: "About"
				imageSource: "asset:///info.png"
				
				onTriggered: {
				    var appInfoPage = appinfo.createObject()
				    navigationPane.push(appInfoPage)
				}
			},
			ActionItem {
				title: "Clear RAM"
				imageSource: "asset:///trash.png"
				
				onTriggered: {
				    cs.clearRAM()
				}
			}/*,
			ActionItem {
				title: "Key Map"
				imageSource: "asset:///keyboard.png"
				
				onTriggered: {
				    var keyMapPage = keymap.createObject()
				    navigationPane.push(keyMapPage)
				}
			}*/
		]
	}
    
	Page {
		id: rootpage
		objectName: "rootpage"
        attachedObjects: [
	        ComponentDefinition {
	            id: romselector
	            source: "rom_selector.qml"
	        },
	        ComponentDefinition {
	            id: rominfo
	            source: "rom_info.qml"
	        },
	        ComponentDefinition {
	            id: appinfo
	            source: "about.qml"
	        },
	        ComponentDefinition {
	            id: keymap
	            source: "key_map.qml"
	        }
		]
        /*keyListeners: KeyListener {
            onKeyPressed: {
                cs.press(event.key)
            }
            onKeyReleased: {
                cs.unpress(event.key)
            }
        }
        onCreationCompleted: {
            cs.setPage(rootpage)
        }*/
        Container {
            id: root_container
	        layout: DockLayout {}
	        ForeignWindowControl {
	            id: foreignControl
	            windowId: "AlmostTIAppID"
	            updatedProperties: WindowProperty.Size | WindowProperty.Position | WindowProperty.Visible
	            visible: boundToWindow
	            topMargin: 0
	            leftMargin: 0
	            topPadding: 0
	            leftPadding: 0
                onCreationCompleted: {
	                cs.setForeignWindow(foreignControl)
				    var romPage = romselector.createObject();
	                navigationPane.push(romPage)
	            }
	            
	            onTouch: {
	                if (event.touchType == TouchType.Down) {
	                    cs.touch(event.localX, event.localY)
	                }
	                else if (event.touchType == TouchType.Up) {
	                    cs.unTouch(event.localX, event.localY)
	                }
	            }
                contextActions: [
	                ActionSet {
	                    title: "AlmostTI Effects"
	                    subtitle: "Enable/Disable Effects"
	                    
	                    ActionItem {
	                        title: "Scanlines"
	                        imageSource: "asset:///scanlines.png"
	                        
	                        onTriggered: cs.toggleScanlines()
	                    }
	                    ActionItem {
	                        title: "Frame Rate"
	                        imageSource: "asset:///framerate.png"
	                                                
	                        onTriggered: cs.toggleFrameRate()
	                    }
		                ActionItem {
		                    title: "Soften"
		                    imageSource: "asset:///soften.png"
		                                            
	                        onTriggered: cs.toggleSoften()
		                }
	                }
	            ]
	        }
	    }
	}
}

