<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Untitled Document</title>
</head>
<body>
	<h1>Update RFID</h1>	
	<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
	$StdID="";
	$RFID="";
	if(isset($_GET['StdID'])){
		$StdID=$_GET['StdID'];
	}
	$sql="SELECT * FROM RFID WHERE StdID LIKE '%$StdID%' ";
	$result=mysqli_query($conn,$sql);
    $no=mysqli_num_rows($result);
	if($no>0){
		while($row=mysqli_fetch_assoc($result)){
         $RFID=$row['RFID'];
		}
	}
	?>
<form action="update.php" method="get">
	RFID<input type="text" name="RFID" value="<?php echo $RFID ?>"/><br>
	<input type="number" name="StdID" value="<?php echo $StdID?>" hidden/><br>
	<button type="submit">Update</button>
</form>	
</body>
</html>