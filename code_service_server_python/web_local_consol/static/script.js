function saveESP(espId) {
    const name = document.getElementById(`name-${espId}`).value;
    const screen = document.getElementById(`screen-${espId}`).value;

    fetch(`/update/${espId}`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ name_room: name, screen: screen })
    })
    .then(response => response.json())
    .then(data => {
        alert(`ESP ${espId} mis à jour.`);
    })
    .catch(error => {
        console.error("Erreur lors de la mise à jour :", error);
    });
}
