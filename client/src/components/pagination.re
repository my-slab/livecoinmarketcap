let component = ReasonReact.statelessComponent("Pagination");

let make = _children => {
  ...component,
  render: _self => <div> <Text value="Pagination" /> </div>
};