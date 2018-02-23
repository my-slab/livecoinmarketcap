let component = ReasonReact.statelessComponent("Text");

let make = (~value: float, _children) => {
  ...component,
  render: _self =>
    <span>
      (value |> Printf.sprintf("%.2f") |> ReasonReact.stringToElement)
    </span>
};