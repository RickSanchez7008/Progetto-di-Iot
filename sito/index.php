<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Controllo Auto</title>
</head>
<body>
    <h1>Controlla la tua auto</h1>
    <form method="post" action="">
        <label for="targa">Inserisci la targa:</label>
        <input type="text" id="targa" name="targa" required>
        <button type="submit">Controlla</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $targa = $_POST["targa"];
        
        include 'config.php';

        $sql = "SELECT * FROM auto WHERE targa = '$targa'";
        $result = $conn->query($sql);

        if ($result->num_rows > 0) {
            while($row = $result->fetch_assoc()) {
                echo "<h2>Risultati per la targa: " . $targa . "</h2>";
                echo "<ul>";
                echo "<li>Motore funzionante: " . $row["motore_funzionante"] . "</li>";
                echo "<li>Freni attivi: " . $row["freni_attivi"] . "</li>";
                echo "<li>Ammortizzatori carichi: " . $row["ammortizzatori_carichi"] . "</li>";
                echo "<li>Olio nel motore: " . $row["olio_motore"] . "</li>";
                echo "<li>Batteria funzionante: " . $row["batteria_funzionante"] . "</li>";
                echo "<li>Luci presenti: " . $row["luci_presenti"] . "</li>";
                echo "<li>Radiatore fuso: " . $row["radiatore_fuso"] . "</li>";
                echo "<li>Gomme lisce: " . $row["gomme_lisce"] . "</li>";
                echo "<li>Tagliando scaduto: " . $row["tagliando_scaduto"] . "</li>";
                echo "<li>Documenti validi: " . $row["documenti_validi"] . "</li>";
                echo "</ul>";
            }
        } else {
            echo "<p>Nessun risultato trovato per la targa: " . $targa . "</p>";
        }

        $conn->close();
    }
    ?>
</body>
</html>
