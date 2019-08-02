using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerControl : MonoBehaviour
{
    // 플레이어 비행체의 이동 속도
    public float Speed = 100.0f;
    // 플레이어 게임 오브젝트의 트랜스폼 컴포넌트
    private Transform myTransform = null;
    public GameObject BulletPrefab = null;
    // Start is called before the first frame update
    void Start()
    {
        myTransform = GetComponent<Transform>();// 캐싱
    }

    // Update is called once per frame
    void Update()
    {
        float axis = Input.GetAxis("Horizontal");
        Vector3 moveAmount = axis * Speed * -Vector3.right * Time.deltaTime;
        myTransform.Translate(moveAmount);
        if(Input.GetKeyDown(KeyCode.Space) == true)
        {
            Instantiate(BulletPrefab, myTransform.position, Quaternion.identity);

        }
    }
}
