let component = ReasonReact.statelessComponent("Percentage");

let make = (~value: float, _children) => {
  ...component,
  render: _self => <span> <Text value="$" /> <Float value /> </span>
};