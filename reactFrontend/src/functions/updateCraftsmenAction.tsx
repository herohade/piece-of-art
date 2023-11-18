import { redirect } from "react-router-dom";

export async function updateCraftsmenAction({ request }: { request: Request }) {
  const formData = await request.formData();
  const updates = Object.fromEntries(formData);
  const { maxDrivingDistance, profilePictureScore, profileDescriptionScore } =
    updates;
  if (maxDrivingDistance) {
    if (import.meta.env.DEV) {
      console.log("maxDrivingDistance", maxDrivingDistance);
    }
    // TODO: update maxDrivingDistance and display success/failure message
  }
  if (profilePictureScore) {
    if (import.meta.env.DEV) {
      console.log("profilePictureScore", profilePictureScore);
    }
    // TODO: update profilePictureScore and display success/failure message
  }
  if (profileDescriptionScore) {
    if (import.meta.env.DEV) {
      console.log("profileDescriptionScore", profileDescriptionScore);
    }
    // TODO: update profileDescriptionScore and display success/failure message
  }
  const urlPath = new URL(request.url).pathname;
  return redirect(urlPath);
}
