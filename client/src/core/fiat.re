let component = ReasonReact.statelessComponent("Percentage");

let make = (~value: float, ~precision=0, _children) => {
  ...component,
  render: _self => <span> <Text value="$" /> <Float value precision /> </span>
};