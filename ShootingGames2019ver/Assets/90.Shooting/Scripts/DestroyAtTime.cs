using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyAtTime : MonoBehaviour 
{
	public float Time = 0.5f;
	// Use this for initialization
	void Start () {
		Destroy(gameObject, Time);
	}
}
