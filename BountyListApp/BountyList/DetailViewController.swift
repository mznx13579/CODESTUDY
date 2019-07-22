//
//  DetailViewController.swift
//  BountyList
//
//  Created by 정성윤 on 22/07/2019.
//  Copyright © 2019 정성윤. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController {
    
    @IBOutlet weak var imgView: UIImageView!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var bountyLabel: UILabel!
    
    var bountyInfo: BountyInfo?

    override func viewDidLoad() {
        super.viewDidLoad()

        updateUI()
    }
    func updateUI() {
        guard let info = bountyInfo else { return }
        imgView.image = info.image
        nameLabel.text = info.name
        bountyLabel.text = "\(info.bounty)"
    }
    @IBAction func close(_ sender: UIButton) {
        dismiss(animated: true, completion: nil)
    }


}
