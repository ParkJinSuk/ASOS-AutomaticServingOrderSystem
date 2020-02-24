

<?php
   $conn = mysqli_connect("106.10.49.227", "sexymandoo", "sexymandoo" , "test");
   $sql = "SELECT Num, Name FROM test";
   $result = mysqli_query($conn, $sql);
   if (mysqli_num_rows($result) > 0) {
   while($row = mysqli_fetch_assoc($result)) {
   echo "테이블 번호: " . $row["Num"]. " 음식:" . $row["Name"]. "<br>";
   }
   }else{
   echo "테이블에 데이터가 없습니다.";
   }
   mysqli_close($conn); // 디비 접속 닫기
?>
