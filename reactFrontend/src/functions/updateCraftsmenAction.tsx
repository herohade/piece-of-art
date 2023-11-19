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

  if (maxDrivingDistanceUpdated) {
    alert("Max driving distance updated to " + maxDrivingDistanceUpdated);
  } else if (profilePictureScoreUpdated) {
    alert("Profile picture score updated to " + profilePictureScoreUpdated);
  } else if (profileDescriptionScoreUpdated) {
    alert(
      "Profile description score updated to " + profileDescriptionScoreUpdated
    );
  }

  return null;
}
