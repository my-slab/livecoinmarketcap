let component = ReasonReact.statelessComponent("Pagination");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <ul className="pagination">
        <li> <Text value="Previous 100" /> </li>
        <li> <Text value="Next 100" /> </li>
      </ul>
    </div>
};