<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "auto_info";

// Creare connessione
$conn = new mysqli($servername, $username, $password, $dbname);

// Controllare connessione
if ($conn->connect_error) {
    die("Connessione fallita: " . $conn->connect_error);
}
?>
