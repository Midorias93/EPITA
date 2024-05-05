// FIXME: This file should handle the rooms API
// Functions may include:
// - fetchRoomConfig (get the configuration of a room)
// - joinRoom (join a room by its slug)
// - listRooms (list all the rooms available)
// - createRoom (create a room)
// - updateRoom (update a room's configuration)
// - deleteRoom (delete a room)

export async function fetchRoomConfig() {
    let token = window.localStorage.getItem('token');
    const slug = window.localStorage.getItem('slug');

    let headers = { Authorization: `Bearer ${token}`};

    let response = await fetch(`/api/rooms/${slug}/config`, {
        headers: headers
    });

    return response;
}