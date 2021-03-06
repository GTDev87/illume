open BsReactNative;

let marginLeftCardContent = 5.;

let headerTextStyle = Style.(style([
  margin(Pct(3.)),
  color(String("gray")),
  textAlign(Left),
  textAlignVertical(Center),
  fontFamily("Arial Rounded MT Bold"),
  flex(1.),
]));

let borderColorDepth = 3.;

let childrenContentStyle = Style.(style([
  marginHorizontal(Pct(marginLeftCardContent)),
]));

let component = ReasonReact.statelessComponent("CardBorderLayout");

let getFooterColor = (footerColor) =>
  switch(footerColor) {
  | None => "gray"
  | Some(color) => color
  };

let make = (~backColor, ~footerText, ~footerColor=?, children) => {
  ...component, 
  render: (_self) =>
    <Card2
      style=Style.(style([
        backgroundColor(String(backColor)),
        borderColor(String("black")),
        borderRadius(borderColorDepth),
        flex(1.),
      ]))
    >
      <Grid
        style=Style.(style([
          borderColor(String("black")),
          borderWidth(borderColorDepth),
          borderRadius(borderColorDepth),
        ]))
      >
        <Row size=1>
          <Col size=2>
            <View style=Style.(style([marginLeft(Pct(10.))]))>
              <IllumeImage />
            </View>
          </Col>
          <Col size=3 />
        </Row>
        <Row size=10 style=childrenContentStyle>
          ...children
        </Row>
        <Row size=1>
          <Text
            value=footerText
            style=Style.(style([
              margin(Pct(3.)),
              color(String(getFooterColor(footerColor))),
              textAlign(Left),
              textAlignVertical(Center),
              flex(1.),
              fontFamily("Arial Rounded MT Bold"),
            ]))
            numberOfLines=1
            minimumFontScale=0.5
            allowFontScaling=true
            adjustsFontSizeToFit=true
          />
        </Row>
      </Grid>
    </Card2>
};