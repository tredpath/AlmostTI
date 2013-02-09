import bb.cascades 1.0

Page {
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        Header {
            title: "ROM Info"
            bottomMargin: 20.0
        }
        Container {
            layout: DockLayout {
            }
            horizontalAlignment: HorizontalAlignment.Fill
            Label {
                text: "ROM File"
                leftMargin: 0.0
                leftPadding: 0.0
            }
            Label {
                text: "Required File Size"
                horizontalAlignment: HorizontalAlignment.Right
            }
        }
        Divider {
        }
        Container {
            layout: DockLayout {
            }
            horizontalAlignment: HorizontalAlignment.Fill
            topMargin: 0.0
            Label {
                text: "TI82.ROM"
                leftMargin: 0.0
                leftPadding: 0.0
            }
            Label {
                text: "131072 Bytes"
                horizontalAlignment: HorizontalAlignment.Right
            }
        }
        Container {
            layout: DockLayout {
            }
            horizontalAlignment: HorizontalAlignment.Fill
            topMargin: 10.0
            Label {
                text: "TI83.ROM"
                leftMargin: 0.0
                leftPadding: 0.0
            }
            Label {
                text: "262144 Bytes"
                horizontalAlignment: HorizontalAlignment.Right
            }
        }
        Container {
            layout: DockLayout {
            }
            horizontalAlignment: HorizontalAlignment.Fill
            topMargin: 10.0
            Label {
                text: "TI83P.ROM"
                leftMargin: 0.0
                leftPadding: 0.0
            }
            Label {
                text: "524288 Bytes"
                horizontalAlignment: HorizontalAlignment.Right
            }
        }
        Container {
            layout: DockLayout {
            }
            horizontalAlignment: HorizontalAlignment.Fill
            topMargin: 10.0
            Label {
                text: "TI85.ROM"
                leftMargin: 0.0
                leftPadding: 0.0
            }
            Label {
                text: "131072 Bytes"
                horizontalAlignment: HorizontalAlignment.Right
            }
        }
        Container {
            layout: DockLayout {
            }
            horizontalAlignment: HorizontalAlignment.Fill
            topMargin: 10.0
            Label {
                text: "TI86.ROM"
                leftMargin: 0.0
                leftPadding: 0.0
            }
            Label {
                text: "262144 Bytes"
                horizontalAlignment: HorizontalAlignment.Right
            }
        }
        Container {
            id: yourFileContainer
	        layout: StackLayout {
	            orientation: LayoutOrientation.TopToBottom
	        }
            horizontalAlignment: HorizontalAlignment.Fill
            
            onCreationCompleted: cs.setYourFileContainer(yourFileContainer)
        }
    }
}
