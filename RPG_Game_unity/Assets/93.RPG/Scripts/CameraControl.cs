using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControl : MonoBehaviour
{
    [Header("카메라기본속성")]
    private Transform myTransform = null;
    public GameObject Target = null;
    private Transform targetTransform = null;

    public enum CameraViewPointState { FIRST, SECOND, THIRD}
    public CameraViewPointState CameraState = CameraViewPointState.THIRD;

    [Header("3인칭 카메라")]
    public float Distance = 5.0f;
    public float Height = 1.5f;
    public float HeightDamping = 2.0f;
    public float RotationDamping = 4.0f;

    [Header("2인칭 카메라")]
    public float RotateSpeed = 25.0f;

    [Header("1인칭 카메라")]
    public float SensitivityX = 5.0f;
    public float SensitivityY = 5.0f;
    private float rotationX = 0.0f;
    private float rotationY = 0.0f;
    public Transform FirstCameraSocket = null;

    // Start is called before the first frame update
    void Start()
    {
        myTransform = GetComponent<Transform>();
        if(Target != null)
        {
            targetTransform = Target.transform;
        }
    }

    void ThirdView()
    {
        float wantedRotationAngle = targetTransform.eulerAngles.y; // 현재 타겟 y축 각도값
        float wanTedHeight = targetTransform.position.y + Height; // 현재 타겟 높이 + 우리가 추가로 높이고 싶은 높이

        float currentRotationAngle = myTransform.eulerAngles.y;
        float currentHeight = myTransform.position.y;

        currentRotationAngle = Mathf.LerpAngle(currentRotationAngle, wantedRotationAngle, RotationDamping * Time.deltaTime);
        currentHeight = Mathf.Lerp(currentHeight, wanTedHeight, HeightDamping * Time.deltaTime);

        Quaternion currentRotation = Quaternion.Euler(0f, currentRotationAngle, 0f);
        myTransform.position = targetTransform.position;
        myTransform.position -= currentRotation * Vector3.forward * Distance;
        myTransform.position = new Vector3(myTransform.position.x, currentHeight, myTransform.position.z);

        myTransform.LookAt(targetTransform);
    }

    void SecondView()
    {
        myTransform.RotateAround(targetTransform.position, Vector3.up, RotateSpeed * Time.deltaTime);
        myTransform.LookAt(targetTransform);
    }

    void FirstView()
    {
        float mouseX = Input.GetAxis("Mouse X");
        float mouseY = Input.GetAxis("Mouse Y");

        rotationX = myTransform.localEulerAngles.y + mouseX * SensitivityX;
        rotationX = (rotationX > 180.0f) ? rotationX - 360.0f : rotationX;

        rotationY = rotationY + mouseY * SensitivityY;
        rotationY = (rotationY > 180.0f) ? rotationY - 360.0f : rotationY;

        myTransform.localEulerAngles = new Vector3(-rotationY, rotationX, 0f);
        myTransform.position = FirstCameraSocket.position;
    }
    private void LateUpdate()
    {
        if(Target == null)
        {
            return;
        }
        if(targetTransform == null)
        {
            targetTransform = Target.transform;
        }
        switch(CameraState)
        {
            case CameraViewPointState.THIRD:
                ThirdView();
                break;
            case CameraViewPointState.SECOND:
                SecondView();
                break;
            case CameraViewPointState.FIRST:
                FirstView();
                break;
        }
    }
}
