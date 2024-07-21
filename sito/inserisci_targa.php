<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Inserisci Nuova Targa</title>
</head>
<body>
    <h1>Inserisci Nuova Targa</h1>
    <form method="post" action="">
        <label for="targa">Targa:</label>
        <input type="text" id="targa" name="targa" required><br><br>

        <label for="motore_funzionante">Motore funzionante:</label>
        <select id="motore_funzionante" name="motore_funzionante">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="freni_attivi">Freni attivi:</label>
        <select id="freni_attivi" name="freni_attivi">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="ammortizzatori_carichi">Ammortizzatori carichi:</label>
        <select id="ammortizzatori_carichi" name="ammortizzatori_carichi">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="olio_motore">Olio nel motore:</label>
        <select id="olio_motore" name="olio_motore">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="batteria_funzionante">Batteria funzionante:</label>
        <select id="batteria_funzionante" name="batteria_funzionante">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="luci_presenti">Luci presenti:</label>
        <select id="luci_presenti" name="luci_presenti">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="radiatore_fuso">Radiatore fuso:</label>
        <select id="radiatore_fuso" name="radiatore_fuso">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="gomme_lisce">Gomme lisce:</label>
        <select id="gomme_lisce" name="gomme_lisce">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="tagliando_scaduto">Tagliando scaduto:</label>
        <select id="tagliando_scaduto" name="tagliando_scaduto">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <label for="documenti_validi">Documenti validi:</label>
        <select id="documenti_validi" name="documenti_validi">
            <option value="si">Si</option>
            <option value="no">No</option>
        </select><br><br>

        <button type="submit">Inserisci</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $targa = $_POST["targa"];
        $motore_funzionante = $_POST["motore_funzionante"];
        $freni_attivi = $_POST["freni_attivi"];
        $ammortizzatori_carichi = $_POST["ammortizzatori_carichi"];
        $olio_motore = $_POST["olio_motore"];
        $batteria_funzionante = $_POST["batteria_funzionante"];
        $luci_presenti = $_POST["luci_presenti"];
        $radiatore_fuso = $_POST["radiatore_fuso"];
        $gomme_lisce = $_POST["gomme_lisce"];
        $tagliando_scaduto = $_POST["tagliando_scaduto"];
        $documenti_validi = $_POST["documenti_validi"];

        include 'config.php';

        $sql = "INSERT INTO auto (targa, motore_funzionante, freni_attivi, ammortizzatori_carichi, olio_motore, batteria_funzionante, luci_presenti, radiatore_fuso, gomme_lisce, tagliando_scaduto, documenti_validi) 
                VALUES ('$targa', '$motore_funzionante', '$freni_attivi', '$ammortizzatori_carichi', '$olio_motore', '$batteria_funzionante', '$luci_presenti', '$radiatore_fuso', '$gomme_lisce', '$tagliando_scaduto', '$documenti_validi')";

        if ($conn->query($sql) === TRUE) {
            echo "Nuova targa inserita con successo!";
        } else {
            echo "Errore: " . $sql . "<br>" . $conn->error;
        }

        $conn->close();
    }
    ?>
</body>
</html>