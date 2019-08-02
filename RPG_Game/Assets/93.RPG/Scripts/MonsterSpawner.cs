using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterSpawner : MonoBehaviour
{
    public GameObject SpawnMonster = null;
    public List<GameObject> MonsterList = new List<GameObject>();
    public int SpawnMaxCount = 50;
    // Start is called before the first frame update
    void Start()
    {
        InvokeRepeating("Spawn", 1f, 3f);
    }
    void Spawn()
    {
        if(MonsterList.Count > SpawnMaxCount)
        {
            return;
        }
        Vector3 spawnPos = new Vector3(Random.Range(-50.0f, 50.0f), 500.0f, Random.Range(-50.0f, 50.0f));

        Ray ray = new Ray(spawnPos, Vector3.down);
        RaycastHit raycastHit = new RaycastHit();
        if(Physics.Raycast(ray, out raycastHit, Mathf.Infinity) == true)
        {
            spawnPos.y = raycastHit.point.y;
        }
        GameObject newMonster = Instantiate(SpawnMonster, spawnPos, Quaternion.identity);
        MonsterList.Add(newMonster);
    }
}
