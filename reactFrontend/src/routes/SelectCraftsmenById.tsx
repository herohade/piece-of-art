import { Form } from "react-router-dom";
import Page from "../components/Page";

// Page for searching the craftsman to update
function SelectCraftsmenById() {
  const content = (
    <div className="contentBody">
      <h1>Search for the craftsman to update by id</h1>
      {/* input form asking for german postcode (5 digits) */}
      <Form method="post" id="craftsman-search-form">
        <label>
          <input type="number" name="craftsmanId" />
        </label>
        <button type="submit">Search</button>
      </Form>
    </div>
  );

  return <Page content={content} />;
}

export default SelectCraftsmenById;
