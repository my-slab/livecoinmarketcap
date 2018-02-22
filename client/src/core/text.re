let component = ReasonReact.statelessComponent("Text");

let make = (~value: string, _children) => {
  ...component,
  render: _self => <span> (ReasonReact.stringToElement(value)) </span>
};