let component = ReasonReact.statelessComponent("Text");

let make = (~value: int, _children) => {
  ...component,
  render: _self =>
    <span> (ReasonReact.stringToElement(string_of_int(value))) </span>
};