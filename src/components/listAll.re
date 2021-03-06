type actions =
  | Search string;

type state = {filterPattern: string};

let initialState () => {filterPattern: ""};

let reducer action _state =>
  switch action {
  | Search pattern => ReasonReact.Update {filterPattern: pattern}
  };

let component = ReasonReact.reducerComponent "ListAll";

let filterPerson pattern => {
  let re = Js.Re.fromStringWithFlags pattern flags::"i";
  fun (person: Model.person) => Js.Re.test person.firstname re || Js.Re.test person.lastname re
};

let personCards pattern people =>
  people |> List.filter (filterPerson pattern) |>
  List.map (fun (person: Model.person) => <PersonCard person key=person.id />);

let search event => Search (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;

let make ::people _children => {
  ...component,
  initialState,
  reducer,
  render: fun {state: {filterPattern}, reduce} =>
    <div>
      <div className="card-container">
        (people |> personCards filterPattern |> Array.of_list |> ReasonReact.arrayToElement)
      </div>
      <div className="control-container">
        <SearchInput
          id="searchInput"
          label="Search"
          value=filterPattern
          onChange=(reduce search)
        />
      </div>
    </div>
};
