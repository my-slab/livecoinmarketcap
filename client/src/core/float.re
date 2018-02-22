let component = ReasonReact.statelessComponent("Text");

let make = (~value: float, _children) => {
  ...component,
  render: _self =>
    <span> (ReasonReact.stringToElement(string_of_float(value))) </span>
};