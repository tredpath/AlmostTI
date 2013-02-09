import bb.cascades 1.0

Page {
    ScrollView {
	    Container {
	        layout: StackLayout {
	        }
	        Header {
	            title: "Key Mapping"
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            topMargin: 10.0
                rightMargin: 0.0
                rightPadding: 0.0
                Label {
	                text: "TI Key"
	            }
	            Label {
	                text: "Blackberry Key"
	                horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Divider {
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
                ImageView {
                    imageSource: "asset:///right.png"
                }
                Label {
	                text: "Backspace"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
                ImageView {
                    imageSource: "asset:///left.png"
                }
                Label {
                    text: "K"
                    horizontalAlignment: HorizontalAlignment.Right
                }
            }
            Container {
                layout: DockLayout {
                }
                horizontalAlignment: HorizontalAlignment.Fill
                ImageView {
                    imageSource: "asset:///up.png"
                }
                Label {
                    text: "O"
                    horizontalAlignment: HorizontalAlignment.Right
                }
            }
            Container {
                layout: DockLayout {
                }
                horizontalAlignment: HorizontalAlignment.Fill
                ImageView {
                    imageSource: "asset:///down.png"
                }
                Label {
                    text: "L"
                    horizontalAlignment: HorizontalAlignment.Right
                }
            }
            Container {
                layout: DockLayout {
                }
                horizontalAlignment: HorizontalAlignment.Fill
                Label {
                    text: "F5"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
                Label {
                    text: "Y"
                    horizontalAlignment: HorizontalAlignment.Right
                }
            }
            Container {
                layout: DockLayout {
                }
                horizontalAlignment: HorizontalAlignment.Fill
                Label {
	                text: "F4"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "T"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "F3"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "R"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "F2"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "E"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "F1"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "W"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "CLEAR"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "Z"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "^"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "X"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "/"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "/"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "*"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "*"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "-"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "-"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "+"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "+"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "ENTER"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "Return"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "CUSTOM"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "$"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "TAN"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "B"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: ")"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: ")"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "9"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "9"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "8"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "8"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "7"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "7"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "6"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "6"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "5"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "5"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "4"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "4"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "3"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "3"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "2"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "2"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "1"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "1"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "0"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "0"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "(-)"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "_"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "MORE"
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                }
	            Label {
	                text: "I"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "DEL"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "P"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "PRGM"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "M"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "COS"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "V"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "("
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "("
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "."
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "."
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "EXIT"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "U"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "XVAR"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: ":"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "STAT"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "N"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "SIN"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "C"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "EE"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "@"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "2ND"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "Q"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "ALPHA"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "A"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "GRAPH"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "S"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "LOG"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "D"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "LN"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "F"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "SQR"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "G"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: ","
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "H"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "STO"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "J"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	        Container {
	            layout: DockLayout {
	            }
	            horizontalAlignment: HorizontalAlignment.Fill
	            Label {
	                text: "ON"
                    textStyle.fontWeight: FontWeight.Bold
                    textStyle.color: Color.White
                }
	            Label {
	                text: "Space"
                    horizontalAlignment: HorizontalAlignment.Right
	            }
	        }
	    }
	}
}
