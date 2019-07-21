using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyControl : MonoBehaviour
{
    public float EnemySpeed = 50.0f;
    private Transform myTransform = null;
    public GameObject Explosion = null;
    // Start is called before the first frame update
    void Start()
    {
        myTransform = GetComponent<Transform>();
    }
    void InitPosition()
    {
        myTransform.position = new Vector3(Random.Range(-60.0f, 60.0f), 50.0f, 0.0f);
    }
    // Update is called once per frame
    void Update()
    {
        Vector3 moveAmount = EnemySpeed * Vector3.back * Time.deltaTime;
        myTransform.Translate(moveAmount);
        if(myTransform.position.y < - 50.0f)
        {
            InitPosition();
        }
    }
    private void OnTriggerEnter(Collider other)
    {
        if(other.tag == "Bullet")
        {
            MainControl.Score += 100;
            Instantiate(Explosion, myTransform.position, Quaternion.identity);
            InitPosition();
            Destroy(other.gameObject);
        }
    }
}
