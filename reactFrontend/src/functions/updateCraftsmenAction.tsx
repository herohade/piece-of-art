import { redirect } from "react-router-dom";
import { patchCraftmanProfile } from "./openApiWrapper";

export async function updateCraftsmenAction({
  params,
  request,
}: {
  params: { id?: number };
  request: Request;
}) {
  const { id } = params;
  if (!id) {
    if (import.meta.env.DEV) {
      console.log("undefined id");
    }
    return null;
  }
  const formData = await request.formData();
  const updates = Object.fromEntries(formData);
  const { maxDrivingDistance, profilePictureScore, profileDescriptionScore } =
    updates;
  if (!maxDrivingDistance && !profilePictureScore && !profileDescriptionScore) {
    if (import.meta.env.DEV) {
      console.log("undefined updates");
    }
    alert("Please fill out at least one field");
    return null;
  }
  const response = await patchCraftmanProfile(
    id,
    maxDrivingDistance ? Number(maxDrivingDistance.valueOf()) : null,
    profilePictureScore ? Number(profilePictureScore.valueOf()) : null,
    profileDescriptionScore ? Number(profileDescriptionScore.valueOf()) : null
  );

  if (response === undefined) {
    return null;
  }

  const { updated } = response;
  if (!updated) {
    return null;
  }

  const {
    maxDrivingDistance: maxDrivingDistanceUpdated,
    profilePictureScore: profilePictureScoreUpdated,
    profileDescriptionScore: profileDescriptionScoreUpdated,
  } = updated;

  const urlPath =
    "/update/" + id + maxDrivingDistanceUpdated
      ? "?maxDrivingDistance=" + maxDrivingDistanceUpdated
      : "" + profilePictureScoreUpdated
      ? "?profilePictureScore=" + profilePictureScoreUpdated
      : "" + profileDescriptionScoreUpdated
      ? "?profileDescriptionScore=" + profileDescriptionScoreUpdated
      : "";
  return redirect(urlPath);
}
