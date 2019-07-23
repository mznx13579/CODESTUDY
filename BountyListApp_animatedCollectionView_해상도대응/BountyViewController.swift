//
//  BountyViewController.swift
//  BountyList
//
//  Created by 정성윤 on 15/07/2019.
//  Copyright © 2019 정성윤. All rights reserved.
//

import UIKit

class BountyViewController: UIViewController, UICollectionViewDataSource, UICollectionViewDelegate, UICollectionViewDelegateFlowLayout {
    
    let bountyInfoList = [
            BountyInfo(name: "brook", bounty: 33000000),
            BountyInfo(name: "chopper", bounty: 50),
            BountyInfo(name: "franky", bounty: 44000000),
            BountyInfo(name: "luffy", bounty: 300000000),
            BountyInfo(name: "nami", bounty: 16000000),
            BountyInfo(name: "robin", bounty: 80000000),
            BountyInfo(name: "sanji", bounty: 77000000),
            BountyInfo(name: "zoro", bounty: 120000000),
        ]
    override func viewDidLoad() {
        super.viewDidLoad()

    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showDetail" {
            let vc = segue.destination as? DetailViewController
            if let index = sender as? Int {
                vc?.bountyInfo = bountyInfoList[index]
            }
        }
    }
    
//    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
//        return bountyInfoList.count
//    }
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return bountyInfoList.count
    }
//    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
//        guard let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath) as? ListCell else {
//            return UITableViewCell()
//        }
//        //img, name, bounty
//        cell.updateUI(bountyInfoList[indexPath.row])
//        return cell
//    }
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        
        guard let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "GridCell", for: indexPath) as? GridCell else { return UICollectionViewCell() }
        
        let info = bountyInfoList[indexPath.item]
        cell.updateUI(info)
        return cell
    }

//    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
//        print("--> \(indexPath.row)")
//        performSegue(withIdentifier: "showDetail", sender: indexPath.row)
//    }
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        performSegue(withIdentifier: "showDetail", sender: indexPath.item)
    }
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        
        let width: CGFloat = (collectionView.bounds.width - 10)/2
        let height: CGFloat = width * 10/7 + 65
        return CGSize(width: width, height: height)
    }
}

//class ListCell : UITableViewCell {
//    @IBOutlet weak var imgView: UIImageView!
//    @IBOutlet weak var nameLabel: UILabel!
//    @IBOutlet weak var bountyLabel: UILabel!
//
//    func updateUI(_ bountyInfo: BountyInfo) {
//        imgView.image = bountyInfo.image
//        nameLabel.text = bountyInfo.name
//        bountyLabel.text = "\(bountyInfo.bounty)"
//    }
//}

class GridCell : UICollectionViewCell {
    @IBOutlet weak var imgView: UIImageView!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var bountyLabel: UILabel!
    
    func updateUI(_ bountyInfo: BountyInfo) {
        imgView.image = bountyInfo.image
        nameLabel.text = bountyInfo.name
        bountyLabel.text = "\(bountyInfo.bounty)"
    }
}
