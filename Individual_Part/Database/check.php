<?php 
include_once('Include/dbConn.php');
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
$RFID="";
if(isset($_GET['RFID'])){
    $RFID=$_GET['RFID'];   
}
$check="";
$name="";
$sql="SELECT * FROM RFID WHERE RFID LIKE '%$RFID%' ";
	$result=mysqli_query($conn,$sql);
    $no=mysqli_num_rows($result);
if($no>0){
    $check="true";
    $id="";
while($row=mysqli_fetch_assoc($result)){
$id=$row['StdID'];
}
$sql1="SELECT * FROM Student WHERE StdID LIKE '%$id%' ";
$result1=mysqli_query($conn,$sql1);
$num=mysqli_num_rows($result1);
if($num>0){
   while($row1=mysqli_fetch_assoc($result1)){
    $name=$row1['Name'];
    $mob=$row1['Mobile_Number'];
   }
}
echo "%".$check."&".$name."^".$mob."@";
}else {
$check="false";
echo $check;
}
?>