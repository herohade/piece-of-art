import { Form, useParams } from "react-router-dom";
import Craftman from "../components/Craftman";
import Page from "../components/Page";

// Page for searching craftsmen by postcode
function UpdateCraftsmenPage() {
  // get id from url: /craftsmen/update/:id
  const { id } = useParams();

  const craftsmanPlaceholder = [
    {
      id: 1,
      name: "Max Mustermann",
      rankingScore: 100,
    },
    {
      id: 2,
      name: "Frieda Musterfrau",
      rankingScore: 100,
    },
    {
      id: 3,
      name: "Anton Mustermann",
      rankingScore: 100,
    },
    {
      id: 4,
      name: "Lena Musterfrau",
      rankingScore: 100,
    },
    {
      id: 5,
      name: "Sebastian Mustermann",
      rankingScore: 100,
    },
  ];

  const craftsman = craftsmanPlaceholder.find(
    (craftsman) => craftsman.id === Number(id)
  );

  const content = craftsman ? (
    <>
      <h1>Update Craftsman {id}</h1>
      <Craftman
        id={craftsman.id}
        name={craftsman.name}
        rankingScore={craftsman.rankingScore}
      />
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
    </>
  ) : (
    <>
      <h1>Craftsman {id} not found</h1>
    </>
  );
  return <Page content={content} />;
}

export default UpdateCraftsmenPage;
