<?php

    error_reporting(E_ALL); 
    ini_set('display_errors',1); 

    include('dbcon.php');


    if( ($_SERVER['REQUEST_METHOD'] == 'POST') && isset($_POST['submit']))
    {

        $Num=$_POST['Num'];
        $Name=$_POST['Name'];

        if(empty($Num)){
            $errMSG = "테이블 번호를 입력하세요.";
        }
        else if(empty($Name)){
            $errMSG = "음식 이름을 입력하세요.";
        }

        if(!isset($errMSG))
        {
            try{
                $stmt = $con->prepare('INSERT INTO test(Num, Name) VALUES(:Num, :Name)');
                $stmt->bindParam(':Num', $Num);
                $stmt->bindParam(':Name', $Name);

                if($stmt->execute())
                {
                    $successMSG = "새로운 주문이 들어왔습니다.";
                }
                else
                {
                    $errMSG = "주문 에러";
                }

            } catch(PDOException $e) {
                die("Database error: " . $e->getMessage()); 
            }
        }

    }
?>

<html>
   <body>
        <?php 
        if (isset($errMSG)) echo $errMSG;
        if (isset($successMSG)) echo $successMSG;
        ?>

        <form action="<?php $_PHP_SELF ?>" method="POST">
		Table Number: <input type = "text" name = "Num" />
		Dish: <input type = "text" name = "Name" />            
		<input type = "submit" name = "submit" />
        </form>
   
   </body>
</html>
