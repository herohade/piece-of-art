import { Form, useLocation, useParams } from "react-router-dom";
import Page from "../components/Page";

// Page for searching craftsmen by postcode
function UpdateCraftsmenPage() {
  // get id from url: /update/:id
  const { id } = useParams();

  const { search } = useLocation();
  const params = new URLSearchParams(search);
  const { maxDrivingDistance, profilePictureScore, profileDescriptionScore } =
    Object.fromEntries(params);

  if (maxDrivingDistance) {
    alert("Max driving distance updated to " + maxDrivingDistance);
  } else if (profilePictureScore) {
    alert("Profile picture score updated to " + profilePictureScore);
  } else if (profileDescriptionScore) {
    alert("Profile description score updated to " + profileDescriptionScore);
  }

  const content = id ? (
    <div className="contentBody">
      <h1>Update Craftsman {id}</h1>
      {/* MAX_DRIVING_DISTANCE */}
      <Form method="post" id="max-driving-distance-form">
        <label>
          Max driving distance:
          <br />
          <input type="number" name="maxDrivingDistance" placeholder="km" />
        </label>
        <button type="submit">Update</button>
      </Form>
      {/* PROFILE_PICTURE_SCORE */}
      <Form method="post" id="profile-picture-score-form">
        <label>
          Profile picture score:
          <br />
          <input type="number" min={0} max={100} name="profilePictureScore" />
        </label>
        <button type="submit">Update</button>
      </Form>
      {/* PROFILE_DESCRIPTION_SCORE */}
      <Form method="post" id="profile-description-score-form">
        <label>
          Profile description score:
          <br />
          <input
            type="number"
            min={0}
            max={100}
            name="profileDescriptionScore"
          />
        </label>
        <button type="submit">Update</button>
      </Form>
    </div>
  ) : (
    <>
      <h1>Craftsman {id} not found</h1>
    </>
  );
  return <Page content={content} />;
}

export default UpdateCraftsmenPage;
