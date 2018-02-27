let component = ReasonReact.statelessComponent("Percentage");

let make = (~value: float, _children) => {
  ...component,
  render: _self => {
    let color = value < 0. ? "#ff3f34" : "#05c46b";
    <span style=(ReactDOMRe.Style.make(~color, ()))>
      <Float value />
      <Text value="%" />
    </span>;
  }
};