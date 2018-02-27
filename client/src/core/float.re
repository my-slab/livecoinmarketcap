let component = ReasonReact.statelessComponent("Text");

let make = (~value: float, ~precision=0, _children) => {
  ...component,
  render: _self =>
    <span>
      (
        value
        |> (
          switch precision {
          | 0 => Printf.sprintf("%.0f")
          | 2 => Printf.sprintf("%.2f")
          | _ => Printf.sprintf("%.2f")
          }
        )
        |> ReasonReact.stringToElement
      )
    </span>
};