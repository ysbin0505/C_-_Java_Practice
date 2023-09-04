# gitstart

https://github.com/ysbin0505/gitstart.git			//부모가 될 레포지토리 주소

https://github.com/ysbin0505/java-practice.git			//자식이 될 레포지토리 주소
	
https://github.com/ysbin0505/C_practice.git			//자식이 될 레포지토리 주소

git init							//바탕화면에 폴더 생성 후 우클릭 -> git bash로 열고 입력

git clone https://github.com/chaehyuenwoo/Itwill_PlayGround.git	//부모 주소 클론 생성

git add .							 

git commit -m 'commit test'					////최초 커밋으로 활성화

git subtree add --prefix=java-practice https://github.com/ysbin0505/java-practice.git main	//자식 서브트리 추가

git subtree add --prefix=C_practice https://github.com/ysbin0505/C_practice.git main		//자식 서브트리 추가

git remote add origin https://github.com/ysbin0505/gitstart.git					//부모 주소 origin remote

git push origin HEAD:main --force								//푸쉬

git remote set-url origin https://chfhddl515@github.com/ysbin0505/gitstart.git			//403에러 발생시

git push origin HEAD:main --force								//다시 푸쉬

