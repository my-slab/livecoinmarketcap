let component = ReasonReact.statelessComponent("Message");

let make = (~columns, ~text, _children) => {
  ...component,
  render: _self => <tr> <td colSpan=columns> <Text value=text /> </td> </tr>
};