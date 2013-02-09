import bb.cascades 1.0

Page {
    Container {
        Header {
            title: "App Info"
        }
        Label {
            text: "Almost TI"
            textStyle.fontWeight: FontWeight.Bold
        }
        Label {
            text: "Original Source:"
        }
        Label {
            text: "Marat Fayzullin"
            horizontalAlignment: HorizontalAlignment.Center
        }
        Label {
            text: "Website:"
        }
        Label {
            text: "fms.komkon.org/ATI85"
            horizontalAlignment: HorizontalAlignment.Center
        }
    }
    attachedObjects: [
    	Invocation {
    	    id: invoke
    	    query: InvokeQuery {
    	        mimeType: "text/html"
    	        uri: "http://fms.komkon.org/ATI85"
            }
        }
    ]
    actions: [
        ActionItem {
            title: "Open Webpage"
            ActionBar.placement: ActionBarPlacement.OnBar
            
            imageSource: "asset:///internet.png"
            
            onTriggered: {
                invoke.trigger("bb.action.OPEN")
            }
        }
    ]
}
