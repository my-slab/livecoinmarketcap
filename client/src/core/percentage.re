let component = ReasonReact.statelessComponent("Percentage");

let make = (~value: float, _children) => {
  ...component,
  render: _self => <span> <Float value /> <Text value="%" /> </span>
};