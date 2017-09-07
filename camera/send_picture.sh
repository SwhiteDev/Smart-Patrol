DIR="/home/swhite/Smart-Patrol"

$DIR/camera/camera

sleep 1

curl -F "image=@test.jpeg" "http://www.jiangh.me/Xungeng/admin/uploadImage"
