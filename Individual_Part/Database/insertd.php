<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
$RF="";
$SI="";
if(isset($_POST['RF'])){
	$RF=$_POST['RF'];
}
if(isset($_POST['SI'])){
	$SI=$_POST['SI'];
}
$sql= "INSERT INTO RFID (RFID, StdID) VALUES ('$RF', '$SI');";
$result=mysqli_query($conn,$sql);
?>
<?php
if($result){
	?>
<script>
alert("saved");
	window.location="DbUI.php";
</script>
<?php
}else{
		?>
<script>
alert("not saved");
<?php
$sqld="DELETE FROM Student WHERE StdID = $SI;";
mysqli_query($conn,$sqld);
?>
	window.location="DbUI.php";
</script>
<?php
}
?>