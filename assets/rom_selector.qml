import bb.cascades 1.0

Page {
    attachedObjects: [
        Sheet {
            id: foldersheet
            content: Page {
                Container {
	                Label {
	                    id: folderLabel
	                    text: ""
	                    horizontalAlignment: HorizontalAlignment.Fill

	                    onCreationCompleted: fb.setFolderLabel(folderLabel)
	                }
	                Container {
	                    horizontalAlignment: HorizontalAlignment.Fill
	                    
	                    ListView {
    	                    id: folderContainer
    	                    
    	                    onCreationCompleted: fb.setFolderDialog(folderContainer)
	                    }
	                }
                }
                
                actions: [
                    ActionItem {
                        title: "Cancel"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        imageSource: "asset:///delete.png"
                        
                        onTriggered: {
                            foldersheet.close();
                            fb.cancel();
                        }
                    },
                    ActionItem {
                        title: "Select"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        imageSource: "asset:///open.png"
                        
                        onTriggered: {
                            foldersheet.close();
                            fb.set();
                        }
                    },
                    ActionItem {
                        title: "Default"
                        ActionBar.placement: ActionBarPlacement.InOverflow
                        imageSource: "asset:///home.png"
                        
                        onTriggered: {
                            foldersheet.close();
                            fb.setDefault();
                        }
                    },
                    ActionItem {
                        title: "SD Card"
                        ActionBar.placement: ActionBarPlacement.InOverflow
                        imageSource: "asset:///sd.png"
                        
                        onTriggered: {
                            foldersheet.close();
                            fb.setSDCard();
                        }
                    }
                ]
            }
        }
    ]
    Container {
        id: rootContainer

        /*property string currentrom: ""
         * DropDown {
         * id: selectrom
         * title: "Select ROM"
         * verticalAlignment: VerticalAlignment.Top
         * horizontalAlignment: HorizontalAlignment.Center
         * 
         * onCreationCompleted: cs.setRomSelector(selectrom)
         * 
         * onSelectedIndexChanged: {
         * rootContainer.currentrom = selectedOption.text
         * }
         * }*/
         Header {
             title: "Recent ROMs"
             visible: recentContainer.visible
         }
        Container {
            visible: recentContainer.visible
            horizontalAlignment: HorizontalAlignment.Fill
            ListView {
                id: recentContainer
                visible: false

	            contextActions: [
	                ActionSet {
	                    title: "Recent Files"
	                    
	                    ActionItem {
	                        title: "Clear List"
	                        imageSource: "asset:///delete.png"
	                        
	                        
	                        onTriggered: cs.clearRecent()
	                    }
	                }
	            ]

                onCreationCompleted: cs.setRecentSelector(recentContainer)
            }
        }
        Header {
            title: "Select ROM"
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            
            ListView {
                id: romContainer
                onCreationCompleted: cs.setRomSelector(romContainer)
            }
            Label {
                text: "No Files Found"
                horizontalAlignment: HorizontalAlignment.Center
                visible: !romContainer.visible
            }
        }
    }
    actions: [
        ActionItem {
            title: "Refresh"
            ActionBar.placement: ActionBarPlacement.OnBar
            imageSource: "asset:///refresh.png"
            
            onTriggered: cs.setRomSelector(romContainer)
        },
        ActionItem {
            title: "ROM Folder"
            ActionBar.placement: ActionBarPlacement.OnBar
            imageSource: "asset:///open.png"
            
            onTriggered: {
                foldersheet.open();
            }
        }
    ]
    titleBar: TitleBar {
        title: "Select a Folder"
    }
}
