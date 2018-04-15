type step =
  | Next(int, int)
  | Previous(int, int);

let component = ReasonReact.statelessComponent("Pagination");

let step = action =>
  (
    switch action {
    | Next(limit, offset) => [
        string_of_int(limit),
        string_of_int(offset + 100)
      ]
    | Previous(limit, offset) => [
        string_of_int(limit),
        string_of_int(offset - 100 < 0 ? 0 : offset - 100)
      ]
    }
  )
  |> (([limit, offset]) => "?limit=" ++ limit ++ "&offset=" ++ offset);

let make = (~limit: int, ~offset: int, _children) => {
  ...component,
  render: _self =>
    <div>
      <ul className="pagination">
        <li
          className="link"
          onClick=(
            event => {
              ReactEventRe.Mouse.preventDefault(event);
              ReasonReact.Router.push(step(Next(limit, offset)));
            }
          )>
          <Text value="Next 100" />
        </li>
        <li
          className="link"
          onClick=(
            event => {
              ReactEventRe.Mouse.preventDefault(event);
              ReasonReact.Router.push(step(Previous(limit, offset)));
            }
          )>
          <Text value="Previous 100" />
        </li>
      </ul>
    </div>
};